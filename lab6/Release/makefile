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
lab6.lss \

FLASH_IMAGE += \
lab6.hex \

EEPROM_IMAGE += \
lab6.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab6.elf secondary-outputs

# Tool invocations
lab6.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab6.map -mmcu=atmega32 -o "lab6.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab6.lss: lab6.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab6.elf  >"lab6.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab6.hex: lab6.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab6.elf  "lab6.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab6.eep: lab6.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab6.elf  "lab6.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab6.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 lab6.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) lab6.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
