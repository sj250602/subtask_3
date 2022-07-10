import matplotlib.pyplot as plt
import numpy as np

runtime = [321.246231,227.395943,214.628613,217.666108,210.834810,208.245340,202.039557,199.116817,201.291116]

utility = [float(1/0.0041189139708682),float(1/0.004313050571966527),float(1/0.005188571099476992),float(1/0.004352936627510456),float(1/0.0045735030276673645),float(1/0.0042588013426255265),float(1/0.005417361001464435),float(1/0.0032966397971757396),float(1/0.00535771440387028)]

resolution = ["700*900","500*700","500*500","300*700","300*400","100*700","300*100","100*200","100*100"]
    
plt.plot(runtime , utility , label = "Utility",color='b')

plt.scatter(runtime,utility)

for i, txt in enumerate(resolution):

    plt.annotate(txt, (runtime[i], utility[i]))

plt.xlabel('Runtime(in seconds)')

plt.ylabel('Utility Metric')

plt.title('Utility vs Runtime Graph for no of frames skipped')

plt.legend()

plt.show()