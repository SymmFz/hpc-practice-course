import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 15})

fig, ax = plt.subplots(figsize=(15, 10))
x = [8, 32, 256, 512, 1024, 4096, 8192]
# gflops_naive  = [0.2, 0.5, 0.6, 0.7, 0.7, 0.6, 0.5]
# gflops_cblas  = [0.1, 2.1, 0.5, 23.8, 39.7, 51.3, 90.1]
# gflops_openmp = [0.02, 3.3, 3.8, 3.4, 3.6, 3.8, 2.7]

gflops_naive  = [1.024, 0.481824, 0.5881377, 0.4978329, 0.5244493, 0.1696641, 0.1257603]
gflops_cblas  = [0.0008490879, 10.92267, 47.73034, 39.33697, 64.35372, 55.66151, 55.21164]
gflops_openmp = [0.0002705416, 0.6619798, 3.351756, 4.401375, 4.592693, 1.022954, 1.048961]
gflops_pthread = [0.0009394495, 0.08274747, 3.780355, 4.192011, 3.771055, 0.9399630, 0.9903438]

plt.plot(x, gflops_naive, label='naive', color='blue', linestyle='-', linewidth=3.0)
plt.plot(x, gflops_cblas, label='cblas', color='green', linestyle='-.', linewidth=3.0)
plt.plot(x, gflops_openmp, label='openmp', color='purple', linestyle=':', linewidth=3.0)
plt.plot(x, gflops_pthread, label='pthread', color='red', linestyle='--', linewidth=3.0)


plt.title('dgemm')
plt.xlabel('matrix size')
plt.ylabel('gflops')
plt.legend()

# plt.savefig('result.png')
plt.show()