import math
import pylab
import numpy 
l = 2**8
m = 501
t = 2**(l/3)
m= numpy.linspace(((2**l)/(t**2)),(2**l),50)
func = ( 1 - math.exp( -1*(math.sqrt(2*m((2**8)**2)/(2**(2**8)))) * (math.exp(math.sqrt(2*m(2**128)/(2**(2**8))))-1)/(math.exp(math.sqrt(2*m(((2**128))**2)/(2**(2**8))))+1)))
pylab.plot( m, func)
