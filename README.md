# pnl-calculator-c

# Run the program

```
mkdir -p build && cd build
cmake ..
make -j
```

After it compiles successfully, run `./pnl_calculator [path to the CSV file] fifo` or `./pnl_calculator [path to the CSV file] lifo`

Example: `./pnl_calculator ../data/sample.csv fifo` or `./pnl_calculator ../data/sample.csv lifo`
