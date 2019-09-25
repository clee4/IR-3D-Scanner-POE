import serial
import numpy as np
import PIL.Image as pili

arduinoComPort = "/dev/ttyACM1"


baudRate = 9600


serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
data = np.zeros((60,71))
raw_data = np.zeros((60,71))
scanning = True

def true_distance(value, x_angle, y_angle):
    low_phi = 90 - y_angle
    true_distance = cos(low_phi)/value
    return true_distance
def calibrate(value, a = 131.9, b = -.003795): #ir sensor input to distance
    return a*np.exp(b*value) #function found via line of best fit from calibration plot
def mapping(value, og_max = 65): #maps the distance to a value corresponding to the range 0-1
    if value > og_max: #any value that is over the max calibrated value gets mapped to 1
        return 1
    else:
        mapped = round(value/og_max, 3)
        print(mapped)
        return mapped
while scanning == True:
  lineOfData = serialPort.readline().decode() #input data
  print(lineOfData)
  filter1 = str(lineOfData).split('\r\n') #isolates data
  filter2 = filter1[0].split(':')
  if len(filter2) == 3:
      for x in range(len(filter2)):
          filter2[x] = int(filter2[x])
      data[filter2[0]][filter2[1]] = mapping(calibrate(filter2[2]))
      raw_data[filter2[0]filter2[1]] = filter2[2]
  if data[59][70] != 0:
      scanning = False

print(data)
np.savetxt('scanner_data_raw.csv', raw_data, delimiter = ',')
np.savetxt('scanner_data_processed.csv', data, delimiter = ',')
image = pili.fromarray(data, 'L')
image.save('WE_DID_IT.png')
image.show()
