################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../object_folder/Circle.cpp \
../object_folder/Ellipse.cpp \
../object_folder/Line.cpp \
../object_folder/Object.cpp 

OBJS += \
./object_folder/Circle.o \
./object_folder/Ellipse.o \
./object_folder/Line.o \
./object_folder/Object.o 

CPP_DEPS += \
./object_folder/Circle.d \
./object_folder/Ellipse.d \
./object_folder/Line.d \
./object_folder/Object.d 


# Each subdirectory must supply rules for building sources it contributes
object_folder/%.o: ../object_folder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\Misc" -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\BBox" -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\object_folder" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


