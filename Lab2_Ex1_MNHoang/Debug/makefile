################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Lab2_MNHoang
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lab2_MNHoang.elf \

MAP_FILES += \
Lab2_MNHoang.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lab2_MNHoang.list \

OBJCOPY_HEX += \
Lab2_MNHoang.hex \

OBJCOPY_BIN += \
Lab2_MNHoang.bin \


# All Target
all: main-build

# Main-build Target
main-build: Lab2_MNHoang.elf secondary-outputs

# Tool invocations
Lab2_MNHoang.elf Lab2_MNHoang.map: $(OBJS) $(USER_OBJS) D:\OneDrive\ -\ VietNam\ National\ University\ -\ HCM\ INTERNATIONAL\ UNIVERSITY\All\ Codes\STMCubeIDE\ Workspace\Lab2\Lab2_Ex1_MNHoang\STM32F103C6UX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Lab2_MNHoang.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\OneDrive - VietNam National University - HCM INTERNATIONAL UNIVERSITY\All Codes\STMCubeIDE Workspace\Lab2\Lab2_Ex1_MNHoang\STM32F103C6UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lab2_MNHoang.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lab2_MNHoang.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lab2_MNHoang.list"
	@echo 'Finished building: $@'
	@echo ' '

Lab2_MNHoang.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Lab2_MNHoang.hex"
	@echo 'Finished building: $@'
	@echo ' '

Lab2_MNHoang.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lab2_MNHoang.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Lab2_MNHoang.bin Lab2_MNHoang.elf Lab2_MNHoang.hex Lab2_MNHoang.list Lab2_MNHoang.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
