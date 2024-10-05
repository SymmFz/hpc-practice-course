import matplotlib.pyplot as plt

plt.rcParams.update({"font.size": 15})

fig, ax = plt.subplots(figsize=(15, 10))
# x = [8, 32, 256, 512, 1024, 4096, 8192]
# gflops_naive  = [0.2, 0.5, 0.6, 0.7, 0.7, 0.6, 0.5]
# gflops_cblas  = [0.1, 2.1, 0.5, 23.8, 39.7, 51.3, 90.1]
# gflops_openmp = [0.02, 3.3, 3.8, 3.4, 3.6, 3.8, 2.7]

# gflops_naive  = [1.024, 0.481824, 0.5881377, 0.4978329, 0.5244493, 0.1696641, 0.1257603]
# gflops_cblas  = [0.0008490879, 10.92267, 47.73034, 39.33697, 64.35372, 55.66151, 55.21164]
# gflops_openmp = [0.0002705416, 0.6619798, 3.351756, 4.401375, 4.592693, 1.022954, 1.048961]
# gflops_pthread = [0.0009394495, 0.08274747, 3.780355, 4.192011, 3.771055, 0.9399630, 0.9903438]

x = [16, 32, 64, 128, 256, 512, 768, 1024, 2048]

ijk = [7.45e-1, 8.00e-1, 6.47e-1, 7.11e-1, 5.45e-1, 5.09e-1, 6.40e-1, 3.98e-1, 1.99e-1]
ikj = [8.19e-1, 8.19e-1, 7.87e-1, 8.27e-1, 8.17e-1, 8.39e-1, 8.63e-1, 8.54e-1, 8.57e-1]
simd = [
    2.048000e00,
    1.820444e00,
    1.713359e00,
    1.065897e00,
    1.504751e00,
    1.472687e00,
    1.613412e00,
    1.444223e00,
    8.528045e-01,
]
simd_with_unroll4 = [
    2.730667e00,
    4.681143e00,
    4.332959e00,
    4.359983e00,
    4.464400e00,
    4.466480e00,
    4.499231e00,
    4.500836e00,
    2.623453e00,
]

mtb = [
    8.192000e-01,
    8.295696e-01,
    8.282591e-01,
    5.694141e-01,
    6.478690e-01,
    5.888499e-01,
    6.626533e-01,
    6.165061e-01,
    4.704800e-01,
]

mtb_with_data_resort = [
    2.730667e00,
    2.730667e00,
    4.519724e00,
    4.554076e00,
    4.355456e00,
    4.102573e00,
    4.525526e00,
    4.556666e00,
    4.238878e00,
]

plt.plot(x, ijk, label="ijk naive", color="blue", linestyle="-", linewidth=3.0)
plt.plot(x, ikj, label="ikj naive", color="green", linestyle="-.", linewidth=3.0)
plt.plot(x, simd, label="SIMD", color="purple", linestyle=":", linewidth=3.0)
plt.plot(
    x,
    simd_with_unroll4,
    label="SIMD with unroll4",
    color="red",
    linestyle="--",
    linewidth=3.0,
)
plt.plot(x, mtb, label="MultiBlocks", linewidth=3.0)
plt.plot(x, mtb_with_data_resort, label="MultiBlocks with data resort", linewidth=3.0)


# plt.plot(x, gflops_naive, label="naive", color="blue", linestyle="-", linewidth=3.0)
# plt.plot(x, gflops_cblas, label="cblas", color="green", linestyle="-.", linewidth=3.0)
# plt.plot(x, gflops_openmp, label="openmp", color="purple", linestyle=":", linewidth=3.0)
# plt.plot(x, gflops_pthread, label="pthread", color="red", linestyle="--", linewidth=3.0)


plt.title("gemm")
plt.xlabel("matrix size")
plt.ylabel("gflops")
plt.legend()

# plt.savefig('result.png')
plt.show()
