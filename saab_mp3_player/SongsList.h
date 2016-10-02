class SongsList {
  public:
    uint8_t count();
    char** get();
    void add(char* element);
    void clear();
  private:
    void resize();
    bool shouldResize();
    uint8_t listSize();
};
