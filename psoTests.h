#ifndef PSO_TESTS
#define PSO_TESTS

class PsoTests
{
public:
  PsoTests();
  ~PsoTests();
  static void runTests();
  static void testGenerateGraph();
  static void testGetStart();
  static void testGetNeighbours();
  static void testGetNeighbourClosestTo();
  static void testUpdateParticle();
};

#endif // PSO_TESTS