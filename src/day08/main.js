const fs = require('fs');

class UnionSet {
  constructor(size) {
    this.pa = Array.from({length: size}, (_, i) => i);
    this.siz = Array.from({length: size}, () => 1);
  }

  find (x) {
    return this.pa[x] === x ? x : (this.pa[x] = this.find(this.pa[x]));
  }

  unite(x, y) {
    let pax = this.find(x);
    let pay = this.find(y);
    if (pax !== pay) {
      this.pa[pax] = pay;
      this.siz[pay] += this.siz[pax];
    }
  }
}

function distanceSquare(a, b) {
  return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}

function readJunctions() {
  const content = fs.readFileSync("input.in");
  const lines = content.toString().split(/\r?\n/);

  return lines.filter(x => x.trim().length > 0).map(line => line.split(",").map(x => parseInt(x)));
}

/**
 * 生成所有节点两两之间的组合 (下标)，并按照距离平方进行排序
 * @param {Array<Array<number>>} junctions 节点数组
 * @returns {Array<Array<number>>} 返回所有节点两两之间的组合 (下标), 按照距离平方进行排序
 */
function generateSortedPairs(junctions) {
  return Array.from({length: junctions.length}, (_, i) => i)
    .flatMap((num, idx, arr) =>
      arr.slice(idx + 1).map(next => [num, next])
    )
    .toSorted((a, b) => {
      let disA = distanceSquare(junctions[a[0]], junctions[a[1]]);
      let disB = distanceSquare(junctions[b[0]], junctions[b[1]]);
      return disA - disB;
    });
}

/**
 * 连接节点函数
 * @param {Array} junctions - 节点数组
 * @param {number} connectCount - 需要连接的节点对数量
 * @returns {UnionSet} 返回连接后的并查集对象
 */
function connect(junctions, connectCount) {

  // 所有 junctions 的两两组合, 按距离排序
  const pairs = generateSortedPairs(junctions);

  const dsu = new UnionSet(junctions.length);

  for (let i = 0; i < connectCount; i++) {
    let [a, b] = pairs[i];
    dsu.unite(a, b);
  }

  return dsu;
}

/**
 * 连接所有节点, 最小生成树 Kruskal
 * @param {Array} junctions - 节点数组
 * @returns {Array} 并查集对象和最后连接的两个点的数组
 */
function connectAllJunctions(junctions) {
  // 所有 junctions 的组合, 按距离排序
  const pairs = generateSortedPairs(junctions);
  const dsu = new UnionSet(junctions.length);

  let components = junctions.length;
  let lastConnect = [];

  for (const [a, b] of pairs) {
    if (dsu.find(a) !== dsu.find(b)) {
      dsu.unite(a, b);
      lastConnect = [a, b];
      components --;

      // 当所有点都连接成一个时停止
      if (components === 1) {
        break;
      }
    }
  }

  return [dsu, lastConnect];
}

function part01() {
  const junctions = readJunctions();

  const dsu = connect(junctions, Math.min(1000, junctions.length));

  const uniqueSizes = new Map();

  for (let i = 0; i < junctions.length; i++) {
    let root = dsu.find(i);
    uniqueSizes.set(root, dsu.siz[root]);
  }

  const sortedSizes = Array.from(uniqueSizes).toSorted((a, b) => b[1] - a[1]);

  return sortedSizes.slice(0, 3)
    .reduce((acc, [root, size]) => acc * size, 1);
}

function part02() {
  const junctions = readJunctions();

  const [_, lastConnect] = connectAllJunctions(junctions);

  return junctions[lastConnect[0]][0] * junctions[lastConnect[1]][0];
}

function main() {
  if (process.argv.length <= 2 || process.argv[2] === "part01") {
    console.log(part01());
  }
  else if (process.argv[2] === "part02") {
    console.log(part02());
  }
  else {
    console.log("Invalid argument");
  }
}

main();
