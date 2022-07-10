import matplotlib.pyplot as plt
import numpy as np

runtime = [67.430067,47.850785,40.967360,39.533950,37.482571,34.970153,32.671135]

utility = [float(1/0.08404451006945587),float(1/0.12835256367039743),float(1/0.15696833621398187),float(1/0.1774714373197177),float(1/0.19308871774466516),float(1/0.23273261483148514),float(1/0.27698984362855655)]

no_of_frames = [12,24,36,48,60,90,120]
    
plt.plot(runtime , utility , label = "Utility",color='b')

plt.scatter(runtime,utility)

for i, txt in enumerate(no_of_frames):

    plt.annotate(txt, (runtime[i], utility[i]))

plt.xlabel('Runtime(in seconds)')

plt.ylabel('Utility Metric')

plt.title('Utility vs Runtime Graph for no of frames skipped')

plt.legend()

plt.show()