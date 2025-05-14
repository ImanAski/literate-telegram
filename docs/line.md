# Line

## struct

```c
typedef struct Line {
  Point start;
  Point end;
  double length;
} Line;
```

## functions

Makes a `Line` and will return the pointer to the `Line` struct.

```c
Line *make_line(Point start, Point end);
```

Takes a `Line` and return the length of the `Line`

```c
int line_length(Line ln);
```

Takes a `Line` and return the string format of the `Line`

```c
char *line_to_string(Line ln);
```
