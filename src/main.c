/*
 * KERNEL MAIN
 */
int main()
{
  *(unsigned short*)(0xB8000) = 0x4141;
  return 0;
}
