#include "common.h"
volatile int stream_en=1;
int picture_count=0;
u32 buffer[65280];  // 480 x 272 / 2픽셀 = 65280개

int status = 0;
int main_menu_status=0;
int read_picture_number=1;


volatile int filter_select=0;

// 사용자가 직접 현재 시간 입력 (예: 업로드 시점 기준)
RTC_Time t;


//0 : 메인화면
//1 : 카메라모드
//2 : 갤러리모드
//3 : 제작자보기 모드
int main() {
	interrupt_init();

    get_sdcard_image(buffer,"LOADING.bin"); //처음 전원화면 출력
    display_image(buffer);
    print_textlcd(0);
    print_textlcd(5);
    sleep(2);

    //업로드할때마다 여기 수정-------
    t.year = 2025;
    t.month = 6;
    t.day = 10;
    t.hour = 16;
    t.min = 41;
    t.sec = 0;
    //업로드할때마다 여기 수정-------


    if(write_time_to_rtc(&t) == XST_SUCCESS) {
        xil_printf("RTC time updated: %02d:%02d:%02d\r\n", t.hour, t.min, t.sec);
    } else {
        xil_printf("Failed to write time to RTC\r\n");
    }

    int frame_count = 0;  // while문 진입 시 프레임 카운터 초기화
    int prev_sec = -1;
    while(1){
    	usleep(10);
        if (read_time_from_rtc(&t) == XST_SUCCESS) {
            //xil_printf("Current Time: %04d-%02d-%02d %02d:%02d:%02d\r\n", t.year, t.month, t.day, t.hour, t.min, t.sec);

            if (prev_sec == -1) {
                prev_sec = t.sec;
            }

            if (t.sec != prev_sec) {
                if (status == 1 && stream_en) {
                	u16 fps_seg=frame_count; //여기서 숫자+fps 출력
                	Segment_Upper(fps_seg);  // FPS를 7-segment에 출력
                    //xil_printf("FPS: %d\n", frame_count);
                }
                frame_count = 0;
                prev_sec = t.sec;
            }
        }

    	if(status == 0){
    		Segment_AllDash();
            print_textlcd(0);
            print_textlcd(6);
    		if(main_menu_status==0){
				get_sdcard_image(buffer,"MAINCAM.bin"); //처음 전원화면 출력
				display_image(buffer);
    		}
    		else if(main_menu_status==1){
				get_sdcard_image(buffer,"MAINIMG.bin"); //처음 전원화면 출력
				display_image(buffer);
    		}
    		else if(main_menu_status==2){
				get_sdcard_image(buffer,"MAINWHO.bin"); //처음 전원화면 출력
				display_image(buffer);
    		}
    	}
    	else if(status ==1){ //카메라모드
    		if(stream_en){
    			get_image(buffer);
    			if (filter_select==0){
    				display_image(buffer);
    			}
    			else if (filter_select==1){
    				display_image(edge_filter(buffer));
    			}
    			else if(filter_select ==2 ){
    				display_image(blur_filter(buffer));
    			}
    			else if(filter_select ==3 ){
    				display_image(blur_filter_simd(buffer));
    			}
    			else if(filter_select == 4){
    				display_image(emboss_filter(buffer));
    			}
    			else if(filter_select == 5){
    				display_image(negative_filter(buffer));
    			}
    			else if(filter_select == 6){
    				display_image(buffer);
    			}
                // stream_en이고 실제로 화면에 출력한 경우에만 FPS 카운트
                frame_count++;
    		}
    		else{
    		}
    	}

    	else if(status ==2){ //갤러리 모드
			stream_en=0;
			print_textlcd(8);

			char str[17];
			memset(str, 0, sizeof(str));
			snprintf(str, sizeof(str), "image%03d.bin", read_picture_number);

			print_textlcd_line2(str);



			Segment_Lower(read_picture_number*100+picture_count);
			if(read_picture_number == 0){
				xil_printf("no files\n");
				status = 0;
				continue;
			}
			read_sdcard_image(buffer, read_picture_number);
			display_image(buffer);


    	}

    	else if(status ==3){ //제작자 모드
            print_textlcd(0);
            print_textlcd(7);
			get_sdcard_image(buffer,"MAINWHO2.bin");
			display_image(buffer);

    	}
    }
    return 0;
}
