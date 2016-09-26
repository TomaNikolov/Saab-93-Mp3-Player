class List {
  public:
    char** get();
    void add(char* element);
  private:
    void resize();
    bool shouldResize();
    uint8_t listSize();
};
