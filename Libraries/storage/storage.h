template <typename T> void storageWrite(int address, T value)
{
    const byte* p = reinterpret_cast<const byte*>(&value);
    for (int i = 0; i < sizeof(value); ++i)
        EEPROM.write(address++, *p++);
}

template <typename T> T storageRead(int address)
{
	T value;
    byte* p = reinterpret_cast<byte*>(&value);
    for (int i = 0; i < sizeof(value); ++i)
        *p++ = EEPROM.read(address++);
    return value;
}