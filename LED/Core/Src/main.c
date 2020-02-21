/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

SPI_HandleTypeDef hspi5;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

SDRAM_HandleTypeDef hsdram1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C3_Init(void);
static void MX_LTDC_Init(void);
static void MX_SPI5_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);


void initDisplay();
void drawAxes();
void drawGraph(int *bins);
void updateGraph(float *bins, int numbins);
void clearLayers();
void fft(cplx buf[], int n);
void fftRecurse(cplx buf[], cplx out[], int n, int step);
void getMagnitude(cplx vals[], float r[], int n);
void normalize(float in[], int n);

static const float maxVoltage = 1.0;
static const int maxFreq = 20000;
static const int minFreq = 10;
float old[8];

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_CRC_Init();
    MX_DMA2D_Init();
    MX_FMC_Init();
    MX_I2C3_Init();
    MX_LTDC_Init();
    MX_SPI5_Init();
    MX_TIM1_Init();
    MX_USART1_UART_Init();
    initDisplay();

    int numBins = 128;
//    float data[numBins];
    float r[128];

//    cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
//    cplx buf[] = {0.0,
//    		0.479425538604203,
//    		0.8414709848078965,
//    		0.9974949866040544,
//    		0.9092974268256817,
//    		0.5984721441039564,
//    		0.1411200080598672,
//    		-0.35078322768961984};

    cplx buf[] = {0.0,
    		0.5144109570936778,
    		0.9113543764606762,
    		1.102101679335574,
    		1.0483659583822245,
    		0.7716549155821225,
    		0.3479841527228045,
    		-0.1107547624708039,
    		-0.48420965569187285,
    		-0.6730542437872358,
    		-0.6233263976401964,
    		-0.3396592653189305,
    		0.11583423317759978,
    		0.6387504721030441,
    		1.1079389797851729,
    		1.4151471087910727,
    		1.4915075102530477,
    		1.324383396221695,
    		0.960447321980995,
    		0.4942397328907523,
    		0.04500857847615769,
    		-0.27249950205585904,
    		-0.37614505450769875,
    		-0.23651741650606384,
    		0.115854442176625,
    		0.5979673361977097,
    		1.0946577666186776,
    		1.4867907770302824,
    		1.6804221666867925,
    		1.6297941492509942,
    		1.3485343307799549,
    		0.9063161168703447,
    		0.41179820546398826,
    		-0.013979822451379853,
    		-0.26723212456282885,
    		-0.28683584265640183,
    		-0.06929390515693945,
    		0.3304120236130974,
    		0.8122872710441424,
    		1.2558116702223094,
    		1.549453449505605,
    		1.617983452322162,
    		1.4409021951902656,
    		1.0574681566531445,
    		0.5570961733833091,
    		0.057476725361032044,
    		-0.3242267556514665,
    		-0.5000506810258052,
    		-0.43275413562081694,
    		-0.14492223837097162,
    		0.2865787507749965,
    		0.7494369561961632,
    		1.1234094107546297,
    		1.3097790220068348,
    		1.2555418445681839,
    		0.9664027260917271,
    		0.5053974934170026,
    		-0.022521031547015347,
    		-0.4961593537631828,
    		-0.8077355551902343,
    		-0.8892476184509548,
    		-0.7291019898945773,
    		-0.3749311816197587,
    		0.07808938253474279,
    		0.5105647808423845,
    		0.8081338293747545,
    		0.8894898742069934,
    		0.7263086199977965,
    		0.3502039147012417,
    		-0.15499158079098305,
    		-0.6737309288788849,
    		-1.0870224833120785,
    		-1.3015431637495127,
    		-1.272467541913695,
    		-1.0144234319929448,
    		-0.5978917227561031,
    		-0.1319319449505179,
    		0.262536996826027,
    		0.48235907485530594,
    		0.4674137688344181,
    		0.21535141376379918,
    		-0.21781650124991592,
    		-0.7314166465497965,
    		-1.2047487437282822,
    		-1.5266245886051484,
    		-1.6225790538796026,
    		-1.4730908983532167,
    		-1.1183523202747356,
    		-0.6484195266172476,
    		-0.18115582488181903,
    		0.1666324421685541,
    		0.3078001714595049,
    		0.20620464510538417,
    		-0.11444152271793573,
    		-0.5763731575496465,
    		-1.0668103014169559,
    		-1.4655698875087597,
    		-1.6744910137797961,
    		-1.6414694815965047,
    		-1.3732171028149651,
    		-0.9336218459681257,
    		-0.4281103063896429,
    		0.02215889821396755,
    		0.3099524636970262,
    		0.36820933303637715,
    		0.1864510815855036,
    		-0.18666205937489666,
    		-0.6552553208538244,
    		-1.0997241901408072,
    		-1.4060299556798894,
    		-1.4936334012578936,
    		-1.3352274743541426,
    		-0.9634376485975369,
    		-0.4628494613167867,
    		0.05068487542947864,
    		0.45839436725895366,
    		0.6676511224949084,
    		0.6346309102774774,
    		0.37502434175797206,
    		-0.0398237500579339,
    		-0.5004014698414647,
    		-0.8858620436770284,
    		-1.0936315229988613,
    		-1.0645429597128708,
    		-0.7973432786214649,
    		-0.3490210069978515,
    		0.1791254306418517,
    		0.6662679379170462};
	fft(buf, 128);
	getMagnitude(buf, r, 128);
	normalize(r, 128);
	updateGraph(r, 128);
    while (1);
}


/**
 * @brief Initialises, turns on and clears the display. It also sets the foreground layer to transparent and the 
 * background layer to white.
 */
void initDisplay()
{
    BSP_LCD_Init();
    BSP_LCD_DisplayOn();

    BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER); //intialize the layers using the buffer
    BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
    clearLayers();

    BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE); //make the background for text on the front layer white
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK); //make the text color black

    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE); //make the background for text on the back layer white
}

/**
 * @brief Clears the layers of the display
 */
void clearLayers(){
    BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
    BSP_LCD_Clear(LCD_COLOR_WHITE); //make the front layer white
    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
    BSP_LCD_Clear(LCD_COLOR_WHITE); //make the back layer white
}

/**
 * @brief Draws the axes for the graph and labels them 
 */
void drawAxes()
{
    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
    int yAxisStart = 10;
    int yAxisLength = 201;
    int yAxisPos = 295;
    BSP_LCD_DrawHLine(yAxisStart, yAxisPos, yAxisLength); //draw the y axis
    int xAxisStart = 210;
    int xAxisLength = 256;
    int xAxisPos = 39;
    BSP_LCD_DrawVLine(xAxisStart, xAxisPos, xAxisLength); //draw the x axis

    char *ylabel = "Volt (V)";
    char *xlabel[11] = {"F", "r", "e", "q", " ", "i", "n", " ", "k", "H", "z"};
    BSP_LCD_SetFont(&Font8);
    BSP_LCD_DisplayStringAt(110, 310, ylabel, LEFT_MODE); //Display the axis title

    for (int a = 0; a < 11; a++)
    {
        BSP_LCD_DisplayStringAt(230, 40 + a * 9, xlabel[a], LEFT_MODE);
    }

    int interval = yAxisLength / 10;
    float vInterval = maxVoltage / 10;
    char caption[4];
    for (int a = 0; a < 11; a++)
    { //this loop makes little lines on the axis as well as the lines for the grid for the y-axis
        if (a != 10)
        {
            BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
            BSP_LCD_DrawVLine(yAxisStart + a * interval, xAxisPos + 1, xAxisLength - 3);
        }

        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DrawVLine(yAxisStart + a * interval, yAxisPos - 3, 7);

        gcvt(maxVoltage - vInterval * a, 2, caption);
        if (a == 0)
        {
            caption[0] = '1';
            caption[1] = '.';
            caption[2] = '0';
            caption[3] = '\0';
        }
        BSP_LCD_DisplayStringAt(yAxisStart + a * interval - 4, yAxisPos + 2, caption, LEFT_MODE); //display intervals next to the axis
        // HAL_Delay(10);                                                                            //the delay makes it look cool
    }

    interval = xAxisLength / 15;
    float fInterval = (maxFreq - minFreq) / 15000.0;
    for (int a = 0; a < 16; a++)
    { //this loop does the same as the previous loop, but for the x-axis
        if (a != 0)
        {
            BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
            BSP_LCD_DrawHLine(yAxisStart, yAxisPos - a * interval, yAxisLength - 3);
        }
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DrawHLine(xAxisStart - 3, yAxisPos - a * interval, 7);

        gcvt(fInterval * a, 2, caption);
        BSP_LCD_DisplayStringAt(xAxisStart + 4, yAxisPos - a * interval - 2, caption, LEFT_MODE); //Display intervals next to the axis
        // HAL_Delay(10);
    }
    // BSP_LCD_Clear(LCD_COLOR_TRANSPARENT);
}

/**
 * @brief Displays the data in the bins on the graph, displaying the lines in positions depending on the number of bins provided.
 * @param bins The array containing the magnitudes of each frequency
 * @param numbins The number of bins in the array
 */
void updateGraph(float *bins, int numbins)
{
//	int same = 0;
//	int i = 0;
//	while((same == 0) && (i < numbins)){
//		if (old[i] != bins[i])
//			same = 1;
//		i++;
//	}
//
//	for (int a = 0; a < numbins; a++){
//		old[a] = bins[a];
//	}
//
//	if (same == 0){
//		return;
//	}

	clearLayers();
	drawAxes();
    BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    int endPosition = 210;          //the x position of the line that reperesents the x axis
    float linePositions[numbins];
    int xAxisYend = 295;
    float binWidth = 256 / numbins;   //the "width" that each bin would occupy on the spectrum, in number of pixels

    for (int a = 0; a < numbins; a++)
    { //determine the positions of the lines that will be drawn
        linePositions[a] = xAxisYend - a * (binWidth) - (binWidth / 2.0);
    }

    int startPosition;
    int yAxisLength = 200;
    for (int a = 0; a < numbins; a++)
    {
        startPosition = endPosition - yAxisLength * bins[a];
        if (numbins < 64){
        	BSP_LCD_DrawRect(startPosition, linePositions[a] - (binWidth / 2), endPosition - startPosition, binWidth - 2);
        	HAL_Delay(10);
        } else {
            BSP_LCD_DrawHLine(startPosition, linePositions[a], endPosition - startPosition);
        }
//        HAL_Delay(1);
    }
    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
}

/**
 * @brief The function used to start of the recursive fft function
 * @param buf The data samples used as input to the fft algorithm
 * @param n The number of samples in the array
 */
void fft(cplx buf[], int n){
    cplx out[n];
    for (int a = 0; a < n; a++){
        out[a] = buf[a];
    }

    fftRecurse(buf, out, n, 1);
}

/** 
 * @brief The recursive part of the fft algorithm.
 * @param buf The input values to the algorithm
 * @param out The output array
 * @param n The number of values in the input array 
 * @param step The step size for the stage 
 */
void fftRecurse(cplx buf[], cplx out[], int n, int step)
{
    if (step < n)
    {
        fftRecurse(out, buf, n, step * 2);
        fftRecurse(out + step, buf + step, n, step * 2);

        for (int a = 0; a < n; a += 2 * step)
        {
            cplx t = cexp(-I * M_PI * a / n) * out[a + step];
            buf[a / 2] = out[a] + t;
            buf[(a + n) / 2] = out[a] - t;
        }
    }
}

void getMagnitude(cplx vals[], float r[], int n)
{
    for (int a = 0; a < n; a++){
        r[a] = cabs(vals[a]);
    }
}

void normalize(float in[], int n)
{
	float max = 0.0;
	for (int a = 0; a < n; a++){
		if (in[a] > max)
			max = in[a];
	}

	for (int a = 0; a < n; a++){
		in[a] = in[a] / max;
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage 
  */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 3;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Activate the Over-Drive mode 
  */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

    /* USER CODE BEGIN CRC_Init 0 */

    /* USER CODE END CRC_Init 0 */

    /* USER CODE BEGIN CRC_Init 1 */

    /* USER CODE END CRC_Init 1 */
    hcrc.Instance = CRC;
    if (HAL_CRC_Init(&hcrc) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN CRC_Init 2 */

    /* USER CODE END CRC_Init 2 */
}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

    /* USER CODE BEGIN DMA2D_Init 0 */

    /* USER CODE END DMA2D_Init 0 */

    /* USER CODE BEGIN DMA2D_Init 1 */

    /* USER CODE END DMA2D_Init 1 */
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DMA2D_Init 2 */

    /* USER CODE END DMA2D_Init 2 */
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

    /* USER CODE BEGIN I2C3_Init 0 */

    /* USER CODE END I2C3_Init 0 */

    /* USER CODE BEGIN I2C3_Init 1 */

    /* USER CODE END I2C3_Init 1 */
    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = 100000;
    hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Analogue filter 
  */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure Digital filter 
  */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C3_Init 2 */

    /* USER CODE END I2C3_Init 2 */
}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

    /* USER CODE BEGIN LTDC_Init 0 */

    /* USER CODE END LTDC_Init 0 */

    LTDC_LayerCfgTypeDef pLayerCfg = {0};

    /* USER CODE BEGIN LTDC_Init 1 */

    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 9;
    hltdc.Init.VerticalSync = 1;
    hltdc.Init.AccumulatedHBP = 29;
    hltdc.Init.AccumulatedVBP = 3;
    hltdc.Init.AccumulatedActiveW = 269;
    hltdc.Init.AccumulatedActiveH = 323;
    hltdc.Init.TotalWidth = 279;
    hltdc.Init.TotalHeigh = 327;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 240;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 320;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    pLayerCfg.FBStartAdress = 0xD0000000;
    pLayerCfg.ImageWidth = 240;
    pLayerCfg.ImageHeight = 320;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN LTDC_Init 2 */

    /* USER CODE END LTDC_Init 2 */
}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void)
{

    /* USER CODE BEGIN SPI5_Init 0 */

    /* USER CODE END SPI5_Init 0 */

    /* USER CODE BEGIN SPI5_Init 1 */

    /* USER CODE END SPI5_Init 1 */
    /* SPI5 parameter configuration*/
    hspi5.Instance = SPI5;
    hspi5.Init.Mode = SPI_MODE_MASTER;
    hspi5.Init.Direction = SPI_DIRECTION_2LINES;
    hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi5.Init.NSS = SPI_NSS_SOFT;
    hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi5.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi5) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI5_Init 2 */

    /* USER CODE END SPI5_Init 2 */
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

    /* USER CODE BEGIN TIM1_Init 0 */

    /* USER CODE END TIM1_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM1_Init 1 */

    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 0;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM1_Init 2 */

    /* USER CODE END TIM1_Init 2 */
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

    /* USER CODE BEGIN FMC_Init 0 */

    /* USER CODE END FMC_Init 0 */

    FMC_SDRAM_TimingTypeDef SdramTiming = {0};

    /* USER CODE BEGIN FMC_Init 1 */

    /* USER CODE END FMC_Init 1 */

    /** Perform the SDRAM1 memory initialization sequence
  */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 7;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 7;
    SdramTiming.WriteRecoveryTime = 3;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN FMC_Init 2 */

    /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, NCS_MEMS_SPI_Pin | CSX_Pin | OTG_FS_PSO_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ACP_RST_GPIO_Port, ACP_RST_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, RDX_Pin | WRX_DCX_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOG, LD3_Pin | LD4_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : NCS_MEMS_SPI_Pin CSX_Pin OTG_FS_PSO_Pin */
    GPIO_InitStruct.Pin = NCS_MEMS_SPI_Pin | CSX_Pin | OTG_FS_PSO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : B1_Pin MEMS_INT1_Pin MEMS_INT2_Pin TP_INT1_Pin */
    GPIO_InitStruct.Pin = B1_Pin | MEMS_INT1_Pin | MEMS_INT2_Pin | TP_INT1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : ACP_RST_Pin */
    GPIO_InitStruct.Pin = ACP_RST_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ACP_RST_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : OTG_FS_OC_Pin */
    GPIO_InitStruct.Pin = OTG_FS_OC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(OTG_FS_OC_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : BOOT1_Pin */
    GPIO_InitStruct.Pin = BOOT1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : OTG_HS_ID_Pin OTG_HS_DM_Pin OTG_HS_DP_Pin */
    GPIO_InitStruct.Pin = OTG_HS_ID_Pin | OTG_HS_DM_Pin | OTG_HS_DP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : VBUS_HS_Pin */
    GPIO_InitStruct.Pin = VBUS_HS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(VBUS_HS_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : TE_Pin */
    GPIO_InitStruct.Pin = TE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TE_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : RDX_Pin WRX_DCX_Pin */
    GPIO_InitStruct.Pin = RDX_Pin | WRX_DCX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pins : LD3_Pin LD4_Pin */
    GPIO_InitStruct.Pin = LD3_Pin | LD4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM6)
    {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */

    /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
