# Point

## struct

```c
typedef struct Point {
  int x;
  int y;
} Point;
```

## functions

Makes a point and will return the pointer to the `Point` struct.

```c
struct Point *make_point(int x, int y)
```

Takes a Point and return the string format of the Point

```c
char *point_to_string(Point pt)
```
