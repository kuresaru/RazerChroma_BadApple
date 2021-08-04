from PIL import Image

sample_positions = [
    (30, [5, 37, 69, 102, 152, 185, 218, 251, 300]),
    (74, [5, 37, 68, 101, 135, 167, 200, 233, 266, 299]),
    (107, [20, 54, 85, 118, 151, 184, 216, 248, 281, 313]),
    (139, [29, 61, 94, 127, 158, 191, 224, 255, 288]),
    (171, [14, 46, 78, 110, 142, 174, 206, 239, 272, 304]),
    (203, [29, 152, 271, 312])
]

frame_total = 5478


with open('samples_data.cpp', 'w') as f:
    f.write("#include <Windows.h>\n\nconst DWORD samples_data[")
    f.write(str(frame_total))
    f.write('][52] = {\n')

    # 读320x240图像序列
    for img_name_i in range(frame_total):
        img_path = 'img_1/%05d.jpg' % (img_name_i + 1)

        print(img_path)
        im = Image.open(img_path)
        pix = im.load()

        f.write("    { ")
        for sample_pos in sample_positions:
            sample_y, sample_xarr = sample_pos
            for sample_x in sample_xarr:
                sample_total_pixels = 0
                sample_average = [0, 0, 0]  # rgb
                for sy in range(max(0, sample_y - 10), min(239, sample_y + 10) + 1):
                    for sx in range(max(0, sample_x - 10), min(319, sample_x + 10) + 1):
                        srgb = pix[sx, sy]
                        sample_average[0] += srgb[0]
                        sample_average[1] += srgb[1]
                        sample_average[2] += srgb[2]
                        sample_total_pixels += 1
                sample_average[0] //= sample_total_pixels
                sample_average[1] //= sample_total_pixels
                sample_average[2] //= sample_total_pixels
                sample_average[0] = min(sample_average[0], 255)
                sample_average[1] = min(sample_average[1], 255)
                sample_average[2] = min(sample_average[2], 255)
                f.write("0x%02X%02X%02X, " %
                        (sample_average[0], sample_average[1], sample_average[2]))
        f.write("},\n")

    f.write("};\n")
