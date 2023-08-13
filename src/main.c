
#include <psp2/kernel/modulemgr.h>
#include <yaml.h>

void _(){
	yaml_get_version_string();
	yaml_parser_scan(NULL, NULL);
	yaml_parser_parse(NULL, NULL);
	yaml_parser_load(NULL, NULL);
	yaml_emitter_emit(NULL, NULL);
	yaml_emitter_open(NULL);
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {
	return SCE_KERNEL_START_SUCCESS;
}
