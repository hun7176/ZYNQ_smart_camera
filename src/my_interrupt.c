
#include "common.h"
int count=0;
XScuGic InterruptController; 	     // Instance of the Interrupt Controller
static XScuGic_Config *GicConfig;    // The configuration parameters of the controller
void interrupt_init(void){
	int Status;
	Status = GicConfigure(INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("GIC Configure Failed\r\n");
		//return XST_FAILURE;
	}
	xil_printf("Interrupt initialized\r\n");
}
int GicConfigure(u16 DeviceId)
{
	int Status;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	GicConfig = XScuGic_LookupConfig(DeviceId);
	if (NULL == GicConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(&InterruptController, GicConfig,
					GicConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the ARM processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler,
			&InterruptController);

	/*
	 * Enable interrupts in the ARM
	 */
	Xil_ExceptionEnable();

	/*
	 * Connect a device driver handler that will be called when an
	 * interrupt for the device occurs, the device driver handler performs
	 * the specific interrupt processing for the device
	 */
	Status = XScuGic_Connect(&InterruptController, INTC_DEVICE_INT_ID,
			   (Xil_ExceptionHandler)ServiceRoutine,
			   (void *)&InterruptController);

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the device and then cause (simulate) an
	 * interrupt so the handlers will be called
	 */
	XScuGic_Enable(&InterruptController, INTC_DEVICE_INT_ID);

	return XST_SUCCESS;
}

void ServiceRoutine(void *CallbackRef)
{
	char pb;

	pb = PUSHBUTTON_mReadReg(XPAR_PUSHBUTTON_0_S00_AXI_BASEADDR, 0);

	PUSHBUTTON_mWriteReg(XPAR_PUSHBUTTON_0_S00_AXI_BASEADDR, 0, 0);

	if ((pb & 1) == 1){ //left button
		if(status==0){
			if(main_menu_status == 0){
				main_menu_status=2;
			}
			else{
				main_menu_status--;
			}
		}

		else if(status==1){
			if(filter_select == 0){
				filter_select=6;
			}
			else{
				filter_select--;
			}
			print_filter_textlcd(filter_select);
		}

		else if(status==2){
			read_picture_number--;
			if(read_picture_number==0){
				read_picture_number=picture_count;
			}
		}


	}
	else if ((pb & 2) == 2){ //right button
		if(status==0){
			if(main_menu_status == 2){
				main_menu_status=0;
			}
			else{
				main_menu_status++;
			}

		}
		else if(status==1){
			if(filter_select == 6){
				filter_select=0;
			}
			else{
				filter_select++;
			}
			print_filter_textlcd(filter_select);
		}
		else if(status==2){
			read_picture_number++;
			if(read_picture_number>picture_count){
				read_picture_number=1;
			}
		}

	}
	else if ((pb & 4) == 4){ // ok button
		if(status == 0){
			if(main_menu_status == 0){
				status=1;
				print_textlcd(0);
				print_textlcd(1);
				stream_en=1;
				Segment_Lower(picture_count);
			}
			else if(main_menu_status == 1){
				status=2;
			}
			else if(main_menu_status == 2){
				status=3;
			}
		}
		else if(status == 1){
			if(count%2==1){
				print_textlcd(0);
				print_textlcd(1);
				stream_en=1;
				Segment_Lower(picture_count);
			}
			else{
				stream_en=0;
				print_textlcd(2);
				picture_count++;
				Segment_Lower(picture_count);
				if(filter_select == 0){
					draw_water_mark(buffer);
					display_image(buffer);
					write_sdcard_image(buffer, picture_count);
				}
				else if (filter_select == 1) {
					u32* new_buffer = edge_filter(buffer);
					draw_water_mark(new_buffer);
					display_image(new_buffer);
					write_sdcard_image(new_buffer, picture_count);
				}
				else if (filter_select == 2 || filter_select ==3) {
					u32* new_buffer = blur_filter(buffer);
					draw_water_mark(new_buffer);
					display_image(new_buffer);
					write_sdcard_image(new_buffer, picture_count);
				}
				else if (filter_select == 4) {
					u32* new_buffer = emboss_filter(buffer);
					draw_water_mark(new_buffer);
					display_image(new_buffer);
					write_sdcard_image(new_buffer, picture_count);
				}
				else if (filter_select == 5) {
					u32* new_buffer = negative_filter(buffer);
					draw_water_mark(new_buffer);
					display_image(new_buffer);
					write_sdcard_image(new_buffer, picture_count);
				}

				else if (filter_select == 6) {
					get_image(buffer);
					display_image(buffer);
					int shoot_count = 3;

					read_time_from_rtc(&t);
					int prev_sec = t.sec;
					while (shoot_count > 0) {
						get_image(buffer);
						draw_number_center(buffer, shoot_count);  // 화면 중앙에 숫자 표시
						display_image(buffer);
						read_time_from_rtc(&t);
						if (t.sec != prev_sec) {
							prev_sec = t.sec;
							shoot_count--;
						}
					}
					get_image(buffer);
					draw_water_mark(buffer);
					display_image(buffer);
					write_sdcard_image(buffer, picture_count);
				}


			}
			count++;
		}
		else if(status == 2){ //갤러리모드일때 확인버튼이 눌릴때 -> 정말 삭제할꺼냐고 물어봐야됨. are you sure delete?
			//display_image(read_errorstate_image("MAINDELY.bin"));
			//sleep(1);

		}

	}
	else if ((pb & 8) == 8){ // cancel button
		status=0;
	}
}
