# number for 11.2
# magicNumbers = {10690, 10744, 12251, 17649, 27280, 42041, 42635, 53798, 56180, 58535, 61041};

# number for 12.0
magicNumbers = [
    10690,
    12251,
    17649,
    24816,
    33360,
    35944,
    36412,
    42041,
    42635,
    44011,
    53799,
    56181,
    58536,
    59222,
    61041,
]


def f1(n: int, byte: int, c: int) -> int:
    for bitIndex in range(8):
        bit = (byte >> bitIndex) & 1
        if bit + ((n - bit) & ~1) == n:
            n = (n - bit) >> 1
        else:
            n = ((c - bit) ^ n) >> 1
    return n


def genPassword(s: str, h: int) -> str:
    for byteIndex in range(len(s) - 1, -1, -1):
        h = f1(h, ord(s[byteIndex]), 0x105C3)

    n1 = 0
    while f1(f1(h, n1 & 0xFF, 0x105C3), n1 >> 8, 0x105C3) != 0xA5B6:
        n1 += 1
        if n1 >= 0xFFFF:
            print("Failed to find a key!")
            return ""

    n1 = int(((n1 + 0x72FA) & 0xFFFF) * 99999.0 / 0xFFFF)
    n1str = f"0000{n1}"
    n1str = n1str[-5:]

    temp = int(n1str[: len(n1str) - 3] + n1str[-2:] + n1str[-3])
    temp = int((temp / 99999.0) * 0xFFFF) + 1
    temp = f1(f1(0, temp & 0xFF, 0x1064B), temp >> 8, 0x1064B)

    for byteIndex in range(len(s) - 1, -1, -1):
        temp = f1(temp, ord(s[byteIndex]), 0x1064B)

    n2 = 0
    while f1(f1(temp, n2 & 0xFF, 0x1064B), n2 >> 8, 0x1064B) != 0xA5B6:
        n2 += 1
        if n2 >= 0xFFFF:
            print("Failed to find a key!")
            return ""

    n2 = int((n2 & 0xFFFF) * 99999.0 / 0xFFFF)
    n2str = "0000" + str(n2)
    n2str = n2str[-5:]

    pass_ = [
        n2str[3],
        n1str[3],
        n1str[1],
        n1str[0],
        "-",
        n2str[4],
        n1str[2],
        n2str[0],
        "-",
        n2str[2],
        n1str[4],
        n2str[1],
    ]
    suffix = "::1"
    return "".join(pass_)[:12] + suffix


if __name__ == '__main__':
    print("Mathematica 12.0 keygen")
    mathID = input("Please input your math ID: ")
    activationKey = "1234-4321-123456"
    s = mathID + "$1&" + activationKey
    print("Activation Key: ", activationKey)
    print("Pick any password from below:")
    for mn in magicNumbers:
        print(genPassword(s, mn))
