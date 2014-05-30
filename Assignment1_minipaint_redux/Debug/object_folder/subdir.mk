################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../object_folder/Circle.cpp \
../object_folder/Ellipse.cpp \
../object_folder/Line.cpp \
../object_folder/Rectangle.cpp \
../object_folder/object.cpp 

OBJS += \
./object_folder/Circle.o \
./object_folder/Ellipse.o \
./object_folder/Line.o \
./object_folder/Rectangle.o \
./object_folder/object.o 

CPP_DEPS += \
./object_folder/Circle.d \
./object_folder/Ellipse.d \
./object_folder/Line.d \
./object_folder/Rectangle.d \
./object_folder/object.d 


# Each subdirectory must supply rules for building sources it contributes
object_folder/%.o: ../object_folder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\Misc" -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\BBox" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


