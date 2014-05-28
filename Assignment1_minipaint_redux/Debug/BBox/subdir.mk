################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BBox/BBox.cpp 

OBJS += \
./BBox/BBox.o 

CPP_DEPS += \
./BBox/BBox.d 


# Each subdirectory must supply rules for building sources it contributes
BBox/%.o: ../BBox/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"E:\2ndSemester\3DS\Github\Minipaint_redux\Assignment1_minipaint_redux\Misc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


