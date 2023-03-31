
# Timetable Generation System

Timetable generator for Institute schedule implemented using C++.





## Abstract

An Institute offers a variety of courses. Some are for a given branch whereas others are for students across a stream of branches. The faculty members teaching these courses are limited, with some professors teaching more than one course. The classrooms on hand are also fixed. Manually scheduling the Timetable can prove to be quite tedious.
## Problem
This project aims to:

- Automate the process of Timetable scheduling.
- Efficiently utilise the resources of the Institute to generate best possible timetable.

## Constraints

- Resources can not overlap timewise
    -   No teacher can hold two classes at the same time
    -	No group can listen for two classes at the same time
    -	No classroom can receive two classes at the same time
    
- Assign classroom depending on strength of students taking the course.

- Account for the fixed location of user-defined lab sessions as well as classes.

- Account for lunch time.

Some soft constraints are:
- Minimize total "idle" for each group (eliminating pause between classes)
- Minimize total "idle time" for each teacher (elimination of pause between classes)
## Solution
INPUTS REQUIRED: 
- .csv file for course offering data.

![image](https://user-images.githubusercontent.com/92890625/229024028-b20009dd-7744-4188-8c61-c0f6ef23f92f.png)

- .csv file on classroom information
![image](https://user-images.githubusercontent.com/92890625/229024378-6773e19d-bae8-4db5-a797-60ca6f03466d.png)

The algorithm for the timetable will create a 5x11 2-D array for each branch of each batch of the Institute . Initially, all slots are free. 

To allocate a time slot to a course, the steps taken are:
- check if slot is free
- check if professor is available
- check if classroom of required strength is free
## Deployment




1) Run the ds.h file

```console
g++ std=c++17 ds.h
```
2) Run maincode.cpp file
```console
g++ std=c++17 maincode.cpp
```
3) Enter lunch slot

## Output
The algorithm for the timetable will generate a 5x11 table for each batch of the Institute showing the timing for each course. 


![image](https://user-images.githubusercontent.com/92890625/229034247-270eb80c-649b-47ec-9137-92db04f4a720.png)

It also generates the schedule of each classroom showing timings of courses allocated to that classroom.

![image](https://user-images.githubusercontent.com/92890625/229035054-55146b6e-89f3-4893-9d8c-63992efc7560.png)
## Authors

- [@Aman Garg](https://github.com/Aman-garg-IITian)
- [@Sanjana Gattraddy](https://github.com/SanjanaGattraddy)
- [@Riya Jain](https://github.com/rjain01)
- [@Dakshi Goel](https://github.com/dakshigoel22)
- [@Prashnat Gautam](https://github.com/prashantgautam96)
- [@Devin](https://github.com/devinchugh)