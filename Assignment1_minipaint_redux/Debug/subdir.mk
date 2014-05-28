################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Canvas.cpp \
../GUI.cpp \
../Test_David_Main.cpp 

OBJS += \
./Canvas.o \
./GUI.o \
./Test_David_Main.o 

CPP_DEPS += \
./Canvas.d \
./GUI.d \
./Test_David_Main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/DavidsMac/Documents/cpp_workspace/Minipaint_redux/Assignment1_minipaint_redux/Misc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


