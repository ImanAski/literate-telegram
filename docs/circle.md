# Line

## struct

```c
typedef struct Circle {
  Point c;
  int r;
} Circle;
```

## functions

Makes a `Circle` and will return the pointer to the `Circle` struct.

```c
Circle *make_circle(Point c, int r);

```

Takes a `Circle` and return the string format of the `Circle`

```c
char *circle_to_string(Circle cr);
```
