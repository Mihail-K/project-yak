echo "// GENERATED FILE. DO NOT EDIT."
echo "extern void isr_common_handler(unsigned interrupt, void* frame);"

for interrupt in `seq 0 255`;
do
    echo "__attribute__((interrupt))"
    echo "static void isr_$interrupt(void* frame)"
    echo "{"
    echo "    isr_common_handler($interrupt, frame);"
    echo "}"
done

echo "void* isr_handlers[256] = {";
for interrupt in `seq 0 255`;
do
    echo "    &isr_$interrupt,"
done
echo "};"
