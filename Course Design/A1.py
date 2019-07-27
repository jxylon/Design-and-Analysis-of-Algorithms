# Tromino谜题，使用分治法思想，图形化界面演示过程
import random
import matplotlib.pyplot as plt
import time

map = []
count = 0
xlist = []
ylist = []
wlist = []


def draw():
    global count
    count += 1
    color = random.random() * len(map)
    while (color in wlist):
        color = random.randint(0, (len(map) * len(map) - 1) / 3)
    for i in range(len(map)):
        for j in range(len(map)):
            if (map[i][j] != 0):
                xlist.append(i)
                ylist.append(j)
                wlist.append(color)
    plt.hist2d(xlist, ylist, bins=len(map), range=[[0, len(map)], [0, len(map)]])
    plt.colorbar()
    # plt.axis('off')
    time.sleep(0.5)
    plt.show()


def init_map():
    """
    初始化方格
    """
    # 用户输入n规模
    print('请输入n')
    scale = input()
    while (not scale.isdigit() or int(scale) < 2):
        print('请重新输入,数字且大于等于2')
        scale = input()
    scale = int(scale)
    n = pow(2, scale)
    # 方格信息 0表示未填充，1表示填充
    # 初始化方格，均为0
    # 生成2维数组
    for i in range(n):
        array = []
        for j in range(n):
            array.append(0)
        map.append(array)
    # 随机生成缺失值
    decy_x = random.randint(0, n - 1)
    decy_y = random.randint(0, n - 1)
    print('decy', decy_x, decy_y)
    # 缺失值填充
    map[decy_x][decy_y] = 2
    draw()
    global count
    count -= 1
    return decy_x, decy_y


def get_quadrant(decy_x, decy_y, start_x, start_y, maplen):
    # 如果缺失坐标与开始坐标相差方格长度的1/2，则划分为一个象限
    if ((decy_x - start_x) < maplen / 2 and (decy_y - start_y) < maplen / 2):
        return 3
    elif ((decy_x - start_x) < maplen / 2 and (decy_y - start_y) >= maplen / 2):
        return 2
    elif ((decy_x - start_x) >= maplen / 2 and (decy_y - start_y) < maplen / 2):
        return 4
    else:
        return 1


def tromino(decy_x, decy_y, start_x, start_y, maplen):
    # 方格2x2之前，分割
    if (maplen > 2):
        qudt = get_quadrant(decy_x, decy_y, start_x, start_y, maplen)
        map_len = int(maplen / 2)
        # 填充剩余的方格
        if (qudt == 1):
            map[start_x + map_len - 1][start_y + map_len - 1] = 1
            map[start_x + map_len][start_y + map_len - 1] = 1
            map[start_x + map_len - 1][start_y + map_len] = 1
        elif (qudt == 2):
            map[start_x + map_len - 1][start_y + map_len - 1] = 1
            map[start_x + map_len][start_y + map_len - 1] = 1
            map[start_x + map_len][start_y + map_len] = 1
        elif (qudt == 3):
            map[start_x + map_len - 1][start_y + map_len] = 1
            map[start_x + map_len][start_y + map_len - 1] = 1
            map[start_x + map_len][start_y + map_len] = 1
        else:
            map[start_x + map_len - 1][start_y + map_len - 1] = 1
            map[start_x + map_len - 1][start_y + map_len] = 1
            map[start_x + map_len][start_y + map_len] = 1
        draw()
        # 分割
        tromino_split(decy_x, decy_y, start_x, start_y, map_len, qudt)
    # 直至方格为2x2，填充
    else:
        for i in range(start_x, start_x + maplen):
            for j in range(start_y, start_y + maplen):
                if (map[i][j] == 0):
                    map[i][j] = 1
        draw()


def tromino_split(decy_x, decy_y, start_x, start_y, map_len, qudt):
    """
    方格一分为四
    :param decy_x:缺失值x坐标
    :param decy_y:缺失值y坐标
    :param start_x:开始x位置
    :param start_y:开始y位置
    :param map_len:方格长度
    :param quad:象限
    """
    if (qudt == 1):
        tromino(decy_x, decy_y, start_x + map_len, start_y + map_len, map_len)  # 第一象限
        tromino(start_x + map_len - 1, start_y + map_len, start_x, start_y + map_len, map_len)  # 第二象限
        tromino(start_x + map_len - 1, start_y + map_len - 1, start_x, start_y, map_len)  # 第三象限
        tromino(start_x + map_len, start_y + map_len - 1, start_x + map_len, start_y, map_len)  # 第四象限
    elif (qudt == 2):
        tromino(start_x + map_len, start_y + map_len, start_x + map_len, start_y + map_len, map_len)  # 第一象限
        tromino(decy_x, decy_y, start_x, start_y + map_len, map_len)  # 第二象限
        tromino(start_x + map_len - 1, start_y + map_len - 1, start_x, start_y, map_len)  # 第三象限
        tromino(start_x + map_len, start_y + map_len - 1, start_x + map_len, start_y, map_len)  # 第四象限
    elif (qudt == 3):
        tromino(start_x + map_len, start_y + map_len, start_x + map_len, start_y + map_len, map_len)  # 第一象限
        tromino(start_x + map_len - 1, start_y + map_len, start_x, start_y + map_len, map_len)  # 第二象限
        tromino(decy_x, decy_y, start_x, start_y, map_len)  # 第三象限
        tromino(start_x + map_len, start_y + map_len - 1, start_x + map_len, start_y, map_len)  # 第四象限
    elif (qudt == 4):
        tromino(start_x + map_len, start_y + map_len, start_x + map_len, start_y + map_len, map_len)  # 第一象限
        tromino(start_x + map_len - 1, start_y + map_len, start_x, start_y + map_len, map_len)  # 第二象限
        tromino(start_x + map_len - 1, start_y + map_len - 1, start_x, start_y, map_len)  # 第三象限
        tromino(decy_x, decy_y, start_x + map_len, start_y, map_len)  # 第四象限


def main():
    # 初始化方格
    decy_x, decy_y = init_map()
    # tromino
    tromino(decy_x, decy_y, 0, 0, len(map))


if __name__ == '__main__':
    main()
