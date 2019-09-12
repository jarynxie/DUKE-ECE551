unsigned power_helper(unsigned x, unsigned y, unsigned curAns) {
  if (y == 1) {
    return curAns;
  }
  curAns *= x;
  return power_helper(x, y - 1, curAns);
}

unsigned power(unsigned x, unsigned y) {
  if ((x == 0 && y == 0) || y == 0) {
    return 1;
  }
  return power_helper(x, y, x);
}
