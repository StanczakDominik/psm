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
lab9.lss \

FLASH_IMAGE += \
lab9.hex \

EEPROM_IMAGE += \
lab9.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lab9.elf secondary-outputs

# Tool invocations
lab9.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lab9.map -Wl,-u,vfprintf -mmcu=atmega32 -o "lab9.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lab9.lss: lab9.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lab9.elf  >"lab9.lss"
	@echo 'Finished building: $@'
	@echo ' '

lab9.hex: lab9.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lab9.elf  "lab9.hex"
	@echo 'Finished building: $@'
	@echo ' '

lab9.eep: lab9.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lab9.elf  "lab9.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lab9.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 lab9.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) lab9.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
