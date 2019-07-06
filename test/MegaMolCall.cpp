class Call {
public:
  bool operator()(unsigned int func) { return true; }
};

int main() {
  Call call1;
  Call *call2 = new Call();
  call1(42);
  bool res = (*call2)(43);
}
