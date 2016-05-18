__kernel void test(__global t_prog *prog)
{
  prog->string[0] = 'A';
  prog->string[1] = 'e';
  prog->string[2] = 'l';
  prog->string[3] = 'l';
  prog->string[4] = 'o';
  prog->string[5] = ',';
  prog->string[6] = ' ';
  prog->string[7] = 'W';
  prog->string[8] = 'o';
  prog->string[9] = 'r';
  prog->string[10] = 'l';
  prog->string[11] = 'd';
  prog->string[12] = '!';
  prog->string[13] = '\0';
  prog->test = 4;
}
