#include <iostream>
using namespace std;

class CPU
{
public:
  virtual void calculate() = 0;
  virtual ~CPU() {}
};

class VideoCard
{
public:
  virtual void show() = 0;
  virtual ~VideoCard() {}
};

class Memory
{
public:
  virtual void storage() = 0;
  virtual ~Memory() {}
};

class IntelCPU : public CPU
{
public:
  virtual void calculate()
  {
    cout << "Intel CPU start calculate" << endl;
  }
};

class IntelVideoCard : public VideoCard
{
public:
  virtual void show()
  {
    cout << "Intel VideoCard start show" << endl;
  }
};

class IntelMemory : public Memory
{
public:
  virtual void storage()
  {
    cout << "Intel Memory start storage" << endl;
  }
};

class LenvenoCPU : public CPU
{
public:
  virtual void calculate()
  {
    cout << "Lenveno CPU start calculate" << endl;
  }
};

class LenvenoVideoCard : public VideoCard
{
public:
  virtual void show()
  {
    cout << "Lenveno VideoCard start show" << endl;
  }
};

class LenvenoMemory : public Memory
{
public:
  virtual void storage()
  {
    cout << "Lenveno Memory start storage" << endl;
  }
};

class Computer
{
public:
  void work()
  {
    cpu->calculate();
    videoCard->show();
    memory->storage();
  }
  Computer(CPU *cpu, VideoCard *videoCard, Memory *memory)
  {
    this->cpu = cpu;
    this->videoCard = videoCard;
    this->memory = memory;
  }
  ~Computer()
  {
    if (cpu != NULL)
    {
      delete cpu;
      cpu = NULL;
    }

    if (videoCard != NULL)
    {
      delete videoCard;
      videoCard = NULL;
    }

    if (memory != NULL)
    {
      delete memory;
      memory = NULL;
    }
  }

private:
  CPU *cpu;
  VideoCard *videoCard;
  Memory *memory;
};

int main(int argc, char const *argv[])
{

  Computer *computer = new Computer(new IntelCPU, new LenvenoVideoCard, new IntelMemory);
  computer->work();

  delete computer;
  return 0;
}
