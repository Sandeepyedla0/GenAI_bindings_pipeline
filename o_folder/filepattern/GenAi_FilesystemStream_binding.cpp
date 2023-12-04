 Generate C++ bindings ('.cpp' file) with the Pybind11 module for a C++ class and provide only the output code without any explanation for :

class FilesystemStream {

    public:
        int counter_; // for debugging (to be removed)
        int map_size_; // size of maps in stream

        /**
         * @brief Construct a new Filesystem Stream object.
         *
         * Creates a data stream of filenames from a filesystem directory iterator.
         *
         * @param path Path to directory to stream filenames from
         * @param recursive True will create a recursive directory iterator that will iterate through subdirectories
         * @param block_size Maximum size of memory the stream will consume at a time
         */
        FilesystemStream(const std::string& path, bool recursive=false, const std::string& block_size="50 MB", const bool is_infer=false);

        FilesystemStream(){}

        ~FilesystemStream();

        /**
         * @brief Get a block of filenames that consumes at most block_size of main memory.
         *
         * @return std::vector<std::string> Vector of filenames
         */
        std::vector<std::string> getBlock();

        /**
         * @brief Get a block of filenames that consumes at most block_size of main memory.
         *
         * @return std::vector<std::string> Vector of filenames
         */
        std::vector<std::string> getBlockIterator();

        /**
         * @brief Get a block of filenames that consumes at most block_size of main memory.
         *
         * @return std::vector<std::string> Vector of filenames
         */
        std::vector<std::string> getBlockTxt();

        /**
         * @brief Write a block of strings to the output file.
         *
         * @param vec Vector to write to output file.
         */
        void writeBlock(const std::vector<std::string>& vec);

        /**
         * @brief Write valid files maps to output file.
         *
         * @param mapping Mapping to write to the output file.
         */
        void writeValidFiles(const Tuple& mapping);

        /**
         * @brief Current size of
         *
         * @param double
         * @return long double
         */
        long double currentSize(const int&, const long double&);

        /**
         * @brief True if no more files, otherwise false
         *
         * @return true No more files remaining
         * @return false More files remain
         */
        bool isEmpty();

        /**
         * @brief Returns path to files
         *
         * @return std::string Path to files
         */
        std::string getFilePath();

        /**
         * @brief Get a block of matched files that uses at most block_size of memory.
         *
         * @return std::vector<Tuple> Block of matched files
         */
        std::vector<Tuple> getValidFilesBlock();

        /**
         * @brief End of vaildFiles.txt has been reached
         *
         * @return true No more matched files remain
         * @return false There are still matched files
         */
        bool endOfValidFiles();

        /**
         * @brief Returns path of validFiles.txt, which stores the matched files
         *
         * @return std::string Path to validFiles.txt
         */
        std::string getValidFilesPath();

        /**
         * @brief Returns the string version of the block_size
         *
         * @return std::string String containing the max amount of memory used
         */
        std::string getBlockSizeStr();

        /**
         * @brief Returns path of the temporary directory used by the FilesystemStream object
         *
         * @return std::string Path to the temporary directory
         */
        std::string getTmpPath();

        Tuple getFileByIndex(int i);

        int getValidFilesSize();

        std::vector<Tuple> getValidFilesSlice(int i, int j, int step);

    private:
        fs::directory_iterator directory_iterator_; // directory iterator to stream from
        fs::directory_iterator end_; // end of directory iterator
        std::vector<std::string> filenames_; // current block of filenames
        std::vector<Tuple> valid_files_; // valid files
        std::string path_; // path to directory
        std::string block_size_str_; // string version of block_size
        std::string tmp_path_; // path to temporary directory
        bool is_infer_; // True if the FilesystemStream is used for inference
        std::string valid_files_path_; // path to validFiles.txt
        std::ifstream valid_files_stream_; // input stream for validFiles.txt
        std::ofstream valid_files_out_stream_; // output stream for validFiles.txt
        std::vector<std::string> valid_files_txt_; // valid files from validFiles.txt
        bool recursive_; // True if the directory iterator is recursive
        std::vector<std::string> block_txt_; // block of filenames from txt file
        std::ifstream block_txt_stream_; // input stream for block_txt_
        std::ofstream block_txt_out_stream_; // output stream for block_txt_
        std::vector<std::string> block_iterator_txt_; // block of filenames from iterator txt file
        std::ifstream block_iterator_txt_stream_; // input stream for block_iterator_txt_
        std::ofstream block_iterator_txt_out_stream_; // output stream for block_iterator_txt_
        std::vector<std::string> block_iterator_txt_out_; // block of filenames from iterator txt file
        std::ifstream block_iterator_txt_out_stream_; // input stream for block_iterator_txt_out_
        std::ofstream block_iterator_txt_out_out_stream_; // output stream for block_iterator_txt_out_
        std::vector<std::string> block_txt_out_; // block of filenames from txt file
        std::ifstream block_txt_out_stream_; // input stream for block_txt_out_
        std::ofstream block_txt_out_out_stream_; // output stream for block_txt_out_
        std::vector<std::string> block_iterator_txt_out_out_; // block of filenames from iterator txt file
        std::ifstream block_iterator_txt_out_out_stream_; // input stream for block_iterator_txt_out_out_
        std::ofstream block_iterator_txt_out_out_out_stream_; // output stream for block_iterator_txt_out_out_
        std::vector<std::string> block_txt_out_out_; // block of filenames from txt file
        std::ifstream block_txt_out_out_stream_; // input stream for block_txt_out_out_
        std::ofstream block_txt_out_out_out_stream_; // output stream for block_txt_out_out_
        std::vector<std::string> block_iterator_txt_out_out_out_; // block of filenames from iterator txt file
        std::ifstream block_iterator_txt_out_out_out_stream_; // input stream for block_iterator_txt_out_out_out_
        std::ofstream block_iterator_txt_out_out_out_out_stream_; // output stream for block_iterator_txt_out_out_out_
        std::vector<std::string> block_txt_out_out_out_; // block of filenames from txt file
        std::ifstream block_txt_out_out_out_stream_; // input stream for block_txt_out_out_out_
        std::ofstream block_txt_out_out_out_out_stream_; // output stream for block_txt_out_out_out_
        std::vector<std::string> block_iterator_txt_out_out_out_out_; // block of filenames from iterator txt file
        std::ifstream block_iterator_txt_out_out_out_out_stream_; // input stream for block_iterator_txt_out_out_out_out_
        std::ofstream block_iterator_txt_out_out_out_out_out_stream_; // output stream for block_iterator_txt_out_out_out_out_
        std::vector<std::string> block_txt_out_