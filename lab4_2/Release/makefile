################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
lab4_2.lss \

FLASH_IMAGE += \
lab4_2.hex \

EEPROM_IMAGE += \
lab4_2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab4_2.elf secondary-outputs

# Tool invocations
lab4_2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab4_2.map -mmcu=atmega32 -o "lab4_2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab4_2.lss: lab4_2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab4_2.elf  >"lab4_2.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab4_2.hex: lab4_2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab4_2.elf  "lab4_2.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab4_2.eep: lab4_2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab4_2.elf  "lab4_2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab4_2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 lab4_2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) lab4_2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
