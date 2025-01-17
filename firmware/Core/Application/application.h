/*
 * application.h
 *
 *  Created on: Jan 17, 2025
 *      Author: T. Burkard, M. Schaer
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

/* ********************** EXTERNAL DECLARATIONS *************************** */
/**
  Setup electrical measurement
 */
void SetupMsmtEle(void);

/**
  Run electrical measurement
 */
void DoMsmtEle(void);

/**
  Setup optical measurement
 */
void SetupMsmtOpt(void);

/**
  Run optical measurement
 */
void DoMsmtOpt(void);

#endif /* APPLICATION_APPLICATION_H_ */
