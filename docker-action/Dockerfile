FROM python:3-slim
RUN pip install requests
COPY entrypoint /entrypoint
RUN chmod +x /entrypoint
ENTRYPOINT ["/entrypoint"]
