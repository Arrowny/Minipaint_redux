################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Misc/Transformation.cpp 

OBJS += \
./Misc/Transformation.o 

CPP_DEPS += \
./Misc/Transformation.d 


# Each subdirectory must supply rules for building sources it contributes
Misc/%.o: ../Misc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\Misc" -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\BBox" -I"C:\Users\Joe\Documents\GitHub\Minipaint_redux\Assignment1_minipaint_redux\object_folder" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


