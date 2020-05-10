

from createfile import write_to_header_file, write_to_source_file

x1 = []

for i in range(0, 320):

    red = 0
    green = 0
    blue = 0

    red = int(i/10)
    red = red << 11
    green = int(i/5)
    green = green << 5
    blue = int(i/10)

    rgb = red + green + blue
    x1.append(rgb)
    print(rgb)

write_to_header_file(x1, "fade_log_seq", "fade_log_seq.h")
write_to_source_file(x1, "fade_log_seq", "fade_log_seq.c", "fade_log_seq.h")
