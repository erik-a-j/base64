
def gen(alpha: str) -> str:
    s = "{\n"
    for row in range(0, 256, 8):
        s += "    "
        for i in range(row, row + 8):
            chr_idx = alpha.find(chr(i))
            if chr_idx != -1:
                s += f"{chr_idx}/*'{alpha[chr_idx]}'*/, "
            else:
                s += "-1, "
        s += '\n'
    s += "};\n"
    return s

print(gen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"))
print(gen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"))