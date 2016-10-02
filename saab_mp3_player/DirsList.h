class DirsList {
  public:
    uint8_t count();
    char** get();
    void add(char* element);
  private:
    void resize();
    bool shouldResize();
    uint8_t listSize();
};
