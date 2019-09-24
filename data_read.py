import serial
import numpy as np

arduinoComPort = "/dev/ttyACM0"


baudRate = 9600


serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
columns = 1 #number of columns
rows = 1 #number of rows
dimx  = 180
dimy = 180
size = True #Whether or not we recieved all the data; True means we havent
scan = True #Whether or not we want to recieve data; True means we do
data = [[]] #Data 180X180 matrix
print(data)

while True:
  lineOfData = serialPort.readline().decode() #input data
  while size == True:
      pass1 = str(lineOfData).split('\r\n') #isolates numbers
      for x in pass1:
          if unicode(x).isnumeric(): #takes the numeric part of input
              data[rows].append(int(x)) #and puts it in the data matrix
              columns += 1 #increases the column count
      if columns == dimx: #restrains number of data per rows
          columns = 0 #resets column number for the new rows
          rows += 1 #moves to the next row
          data.append([]) #sets up next row
      if rows == dimy: #restrains number of rows per row
          size = False #stops adding data to the matrix
          scan = False # stops getting data, moves on to calibration

  print(data) #prints matrix with new data
raw_data = data
### TODO: apply calibration to data

def calibrate(value, a = 131.9, b = -.003795):
    return a*np.exp(b*value) #function found via line of best fit from calibration plot

for rows in data: #go into each row
    for column in rows: #go into each value in each row
        q = calibrate(column) #calibrate it
        data[rows[column]] = q #save it into data
calibrated_data = data
print(data)
### TODO: vizualization: distance to grayscale
# max = 0
# for rows in data:
#     if max(rows) > max:
#         max = max(rows)
#
# def map(value, start_max, end_max):
#     return value * end_max / start_max
#
# for rows in data:
#     for columns in rows:
#         data[rows[columns]] = map(columns, max, 1)
#
# grayscale_data = data
#
# array = np.zeros(dimx,dimy)
#
# for rows in data:
#     for columns in rows:
#         array[rows, columns] = columns
