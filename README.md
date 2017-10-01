# generic-static-linked-list

This is a generic implementation for a static (single) linked list.

To be more clear, it is more an implementation for the linking of nodes in a list (adding/deleting/...).

You could build a dynamically-allocated linked list on top of this.
The code here could than be used for the linking between nodes.

# Tests
The tests are made using [Ceedling](https://github.com/ThrowTheSwitch/Ceedling).
Al the sources to run the tests are committed.
Just check out this repo and you can run the tests:
```bash
$> git clone https://github.com/laurensmiers/generic-static-linked-list.git

$> cd generic-static-linked-list

$> ceedling test:all
```

# TODO

1. Make an XOR list to have double linked list functionality
We could then implement ll_prev_node and foreach_reverse