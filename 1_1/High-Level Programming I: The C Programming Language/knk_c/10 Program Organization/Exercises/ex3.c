int i;              /* ex::i */

int main(int i) {
    if (true) {
        int i;      /* if::i */
    }

    for (int i = 0; i < 10; i++) {} /* for::i */
    for (int j = 0; j < 10; j++) {
        int i;                      /* for::i */
    }

    while (true) {
        int i;      /* while::i */
        break;
    }

    do {
        int i;      /* do::i*/
    } while (false);

    {
        int i;  /* block::i */
    }

    return 0;
}
