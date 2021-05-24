#ifndef TELUAEXTENDED_H
#define TELUAEXTENDED_H

namespace TE::Lua {
  class Table;

  class Extended {
  public:
    Extended();

    virtual void SetData(Table &luaTable) = 0;
    virtual Table GetData()               = 0;

  private:
  };
}

#endif
