# graph / 6/21/2026

## 1.Motivation
- Leaned from class.
- https://www.coursera.org/learn/cs-fundamentals-3/programming/pK1Sk/graph-search-project

## 2.Working Functions
- compressionForPrint()

### Expected Output
- expected output
```
  input :
  abbcccddddeeeee
  output :
  1100 1101 1101 111 111 111 10 10 10 10 0 0 0 0 0
```

### How it works
- Counts the frequency of each char.
- Sort them by frequency in descending order..
- Assigns shorter bit if it has higher frequency.
- Change string line to bit.
