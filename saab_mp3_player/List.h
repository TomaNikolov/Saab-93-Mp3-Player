class List {
  public:
    char** init();
    void add(char* element);
  private:
    void resize();
    bool shouldResize();
    uint8_t listSize();
};
