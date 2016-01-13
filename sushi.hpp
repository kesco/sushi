#ifndef __SUSHI_HPP__
#define __SUSHI_HPP__

namespace sushi
{

struct Protocol
{
  virtual ~Protocol()
  {
    /* Empty */
  }
  virtual char* encode() = 0;
};

struct IntegerProtocol: Protocol
{
  virtual char* encode() override;
private:

};

struct BulkStringProtocol: Protocol
{
  virtual char* encode() override;
};

struct ArrayProtocol: Protocol
{
  virtual char* encode() override;
};

}

#endif /* __SUSHI_HPP__ */
