# coms3270P1
To run the program run the following commands:
1. make stat
2. ./stat < "name of file"
3. where "name of file" is a set of points with height

To run the program to create an image:
1. make display
2. ./display < "name of file"
3. display out.gif



this program can currently be used to find the high point, low point, and average of a set of points.
Given that the set of points are formated in the way of "double double double" each seperated by a space

the program can also create an image based on the depth of the points given and it will be shaded blue based on how deep the water is at each point

Known Errors/ issues:
if the input is not a set of points there is will be an error and it will hang.
the points in the file need to be formated correctly in order to print the image correctly
if wdmax is too low or too high the .gif created will look weird
