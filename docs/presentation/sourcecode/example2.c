int main(int argc, char** argv)
{
    // local variables
    int var;

    // initializations
    init();

    // endless loop
    while(1)
    {
        var = read_buttons();
        ++var;
        write_leds(var);
    }
}
