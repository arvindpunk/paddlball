void p_plot(int a, int b) {
    line(a, getmaxy() - 4, b, getmaxy() - 4);
}

void p_left(int & pos) {
    pos = pos - 5;
    setcolor(15);
    p_plot(pos - 40, pos - 36);
    setcolor(0);
    p_plot(pos + 41, pos + 45);
}

void p_rite(int & pos) {
    pos = pos + 5;
    setcolor(15);
    p_plot(pos + 36, pos + 40);
    setcolor(0);
    p_plot(pos - 45, pos - 41);
}