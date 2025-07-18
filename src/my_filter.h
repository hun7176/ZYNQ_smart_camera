/*
 * my_filter.h
 *
 *  Created on: 2025. 6. 6.
 *      Author: IT2-000
 */

#ifndef SRC_MY_FILTER_H_
#define SRC_MY_FILTER_H_


u32* blur_filter(u32 *buffer);
u32* edge_filter(u32 *buffer);
u32* negative_filter(u32 *buffer);
u32* emboss_filter(u32 *buffer);

#endif /* SRC_MY_FILTER_H_ */
