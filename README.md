# BMSSP
The implementation of "Breaking the Sorting Barrier for Directed Single-Source Shortest Paths" by R. Duan, J. Mao, X. Mao, X. Shu, and L. Yin  
https://arxiv.org/abs/2504.17033v1

Verified by AOJ judge: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=10625320#1

### How to build
```
g++ -std=c++17 -I. main.cpp impl/block_heap.cpp impl/shortest_path.cpp impl/heap.cpp -o main
```
### Caveats

The data structure in Lemma 3.3 is not implemented. It is replaced by a normal priority queue. This means that the time complexity for ``insert`` is $O(\log N)$
instead of amortized $O(\max(1,\log(N/M)))$. The same for ``BatchPrepend`` and ``Pull``.

補題3.3のデータ構造はこのレポジトリでは実装されておらず、一般的な優先度付きキューに置き換えられています。これによって、``insert``の計算量は論文中のならし $O(\max(1,\log(N/M)))$ではなく、 $O(\log N)$となっています。
``BatchPrepend``と``Pull``も同様です。
