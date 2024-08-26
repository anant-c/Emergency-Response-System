#include "sendMail.h"
#include <string>
#include <ESP_Mail_Client.h>

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "SENDER_GMAIL_ACCOUNT"
#define AUTHOR_PASSWORD "SENDER_GMAIL_APP_PASSWORD"

#define RECIPIENT_EMAIL "01fe21bec263@kletech.ac.in"

SMTPSession smtp;

void smtpCallback(SMTP_Status status){
  Serial.println(status.info());
  if(status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for(size_t i=0; i<smtp.sendingResult.size(); i++){
      SMTP_Result result = smtp.sendingResult.getItem(i);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    smtp.sendingResult.clear();
  }  
}

void sendSOS(std::string msg){
    MailClient.networkReconnect(true);
    smtp.debug(1);
    smtp.callback(smtpCallback);
    Session_Config config;
    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = AUTHOR_EMAIL;
    config.login.password = AUTHOR_PASSWORD;
    config.login.user_domain = "";

    config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
    config.time.gmt_offset = 3;
    config.time.day_light_offset = 0;

    SMTP_Message message;

    message.sender.name = F("ESP-Car");
    message.sender.email = AUTHOR_EMAIL;
    message.subject = F("Emergency SOS!");
    message.addRecipient(F("Authorities"), RECIPIENT_EMAIL);

    std::string location = "Find my location in the link!";
    std::string textMsg =  msg + "\n" + location;
    
    message.text.content = textMsg.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    
    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
    message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

    if (!smtp.connect(&config)){
        ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
        return;
    }

    if (!smtp.isLoggedIn()){
        Serial.println("\nNot yet logged in.");
    }
    else{
        if (smtp.isAuthenticated())
        Serial.println("\nSuccessfully logged in.");
        else
        Serial.println("\nConnected with no Auth.");
    }

    if (!MailClient.sendMail(&smtp, &message))
        ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());

}